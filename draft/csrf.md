# クロスサイトリクエストフォージェリ(CSRF)

名前が長くて、馴染みのない単語が並んでいるので、まずは実際に被害にあってみましょう。

まず、自分のアカウントでサンプルアプリケーションにログインし、ブログの一覧を確認します。

(画像)

外部のサイトにあるものと仮定して、次のファイルを開いてください。

```text
outside/csrf/index.html
```

(画像)

サンプルアプリケーションのブログの一覧を再度開き、内容を確認します。
すると、自分のアカウントでブログが追加されています…。
勝手に書き込まれた内容が、詐欺サイトや悪質な商品の販売ページへのリンク、政治的な主張だったりしたら、これを見たユーザー達は我々のサービスのことをどういうふうに感じるでしょう…。

(画像)

## 何をしたの？

ソースを確認してみましょう。

```html
<!-- outside/csrf/index.html -->
<!doctype html>

<html lang="en">
<head>
  <meta charset="utf-8">
  <title>CSRF Sample</title>
  <meta name="description" content="CSRF Sample">
  <meta name="author" content="ken1flan">
</head>

<body>
  <h1>CSRF Sample</h1>
  <img src='./test.jpg' height=100><br>
  <img src='http://localhost:3000/users/1/blogs/create?blog[title]=hello&blog[body]=CSRF&blog[status]=published' style='display: none;'>
</body>
</html>
```

`display: none`の`img`があり、その`src`にブログを作成するURLが書かれています。
サンプルアプリケーションにログインしていたので、まんまとブログが投稿されてしまったのです。

他にも「かわいいにゃんこ画像がいっぱいあるよ！」のような興味を惹くようなテキストにリンクとしたりも考えられます。

## サンプルアプリケーションはどうなっている？

`config/routes.rb`を見ると、わざわざ`GET`でブログを投稿できるようにしてあります。
なので、ログイン中のセッションが残っているときにURLをGETされるとブログを投稿させてしまえるのです。


```ruby
# config/routes.rb
  :
  resources :users do
    get '/blogs/create', to: 'users/blogs#create', as: 'create_blog'
    resources :blogs, module: :users
  end
  :
```

## 直し方

特に理由がないのであれば`GET`をやめて`POST`に変えることがRailsでは一番簡単で確実な方法です。
通常、`rails new`すると作られる`app/controllers/application_controller.rb`には`protect_from_forgery with: :exception`が書かれており、これによって`GET`以外はリクエストにセキュリティトークンを自動で含めてくれます。

```ruby
# config/routes.rb
  :
  resources :users do
    # XXX: GETでブログの投稿をさせないようにする。
    # get '/blogs/create', to: 'users/blogs#create', as: 'create_blog'
    resources :blogs, module: :users
  end
  :
```

要件的にどうしても外せない場合には、本人のセッションを使うので、リファラーを偽装することはできません。ですので、正しいページからのアクセスかどうかリファラーを確認します。

```ruby
# TODO
```
