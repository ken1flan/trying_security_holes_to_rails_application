
= 正規表現


ここでは、正規表現のスキをついて他のユーザに対してクロスサイトスクリプティングを仕掛けます。その後、問題の箇所を確認し、修正方法について検討します。


== 試し方


ログインした状態で、右上のアカウント名のドロップダウンメニューから、@<tt>{Profile}をクリックすると、プロフィールが表示されます。



//image[profile][プロフィールへ]{
//}




@<tt>{Edit}ボタンで編集ができます。
ここで@<tt>{Homepage}の項目にJavascriptを設置してみましょう。
@<tt>{Homepage}は@<tt>{<a>}タグとして設置されるので、@<tt>{javascript: alert('DANGER!!')}のように設定する必要があります。



直接入れてもうまくいきません。
この値は検証されているので、@<tt>{http://〜}や@<tt>{https://〜}のような値でないと入りません。



//image[invalid_error][プロフィール編集]{
//}




複数行にして、一行目はJavascript、2行目の行頭が@<tt>{http://}で始まるようにしたらどうでしょう？
この編集ページのフォームは@<tt>{<input type='text'>}ですが、複数行入れることは可能です。例えば、プロフィール編集画面のHTMLを開発者ツールなど@<tt>{<input type="text" 〜>}を@<tt>{<textarea>}に変えられます。



//image[text2textarea][textからtextareaに]{
//}




そうした上で、後述のデータを入力して保存してみてください。
1行目文末でコメントにし、その後コメントとして2行目にURLが記載されています。


//emlist[][javascript]{
javascript: alert('DANGER!!'); /*
https://example.com */
//}


保存後、@<tt>{Homepage}リンクをクリックしてみてください。@<tt>{alert}が表示されたかと思います。



//image[it_works][保存できたし、動いたし…]{
//}



== どうなっているのでしょう？


検証部分がおかしいので、modelを確認します。
@<tt>{homepage}の@<tt>{format}の設定を見ると正規表現で書かれています。
@<tt>{/^https?:\/\/.*$/}は@<tt>{http://}か@<tt>{https://}で始まる…と書かれています。一見よさそうですが、先頭と末尾を表すのに@<tt>{^}と@<tt>{$}を使っています。


//emlist[][ruby]{
# app/models/user.rb
class User < ApplicationRecord
    :
    :
  validates :homepage, format: { with: /^https?:\/\/.*$/, multiline: true }, allow_blank: true
end
//}


Rubyでは@<tt>{^}は行の先頭、@<tt>{$}は行末を表します。ですので、複数行の入力に対してこのパターンを使うと、マッチしてしまいます。


//emlist[][ruby]{
"javascript: alert('DANGER!'); /*
http://example.com
*/".match?(/^https?:\/\/.*$/)
# => true
//}


Rubyの正規表現には文字列の先頭、末尾を表す@<tt>{\A}と@<tt>{\Z}があります。これらを使えば複数行でも正しく判定できます。


//emlist[][ruby]{
"javascript: alert('DANGER!'); /*
http://example.com
*/".match?(/\Ahttps?:\/\/.*\Z/)
# => false
//}

== 修正案


ここの機能で、ホームページのURLであることの検証であるならば、@<tt>{\A}と@<tt>{\Z}に変えることが妥当でしょう。


//emlist[][ruby]{
# app/models/user.rb
class User < ApplicationRecord
    :
    :
  validates :homepage, format: { with: /\Ahttps?:\/\/.*\Z/ }, allow_blank: true
end
//}
