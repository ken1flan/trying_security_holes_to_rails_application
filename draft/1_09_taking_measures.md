# 対策しよう

ちょっとした間違いでユーザに損害を与える可能性があることが伝わったでしょうか？
ここでは、このようなミスをしないための静的解析ツールのGemやWebサービスについて紹介します。
お仕事で使われておられる方も多いかもしれません。

## [Brakeman](https://github.com/presidentbeef/brakeman)

Railsのための、セキュリティ脆弱性を検知する静的コード解析ツールがあります。
アプリケーションのルートディレクトリで`brakeman`と実行するだけで、コード全体をチェックしてくれます。
サンプルアプリケーションをチェックしたものが次の通りです。

仕掛けてあるクロスサイトスクリプティング、バリデーションの正規表現の不備、オープンリダイレクタ、SQLインジェクションが検知されています。

```plain
$ brakeman

== Brakeman Report ==

Application Path: /Users/ken1flan/src/security_sample
Rails Version: 5.2.2
Brakeman Version: 4.3.1
Scan Date: 2019-03-13 19:35:00 +0900
Duration: 0.821549 seconds
Checks Run: BasicAuth, BasicAuthTimingAttack, ContentTag, CreateWith, CrossSiteScripting, DefaultRoutes, Deserialize, DetailedExceptions, DigestDoS, DynamicFinders, E
  :
  :
== Warning Types ==

Cross-Site Scripting: 2
Format Validation: 1
Redirect: 1
SQL Injection: 3

Confidence: High
Category: Cross-Site Scripting
Check: CrossSiteScripting
Message: Unescaped model attribute
Code: Blog.find(params[:id]).user.measurement_tag.body
File: app/views/blogs/show.html.erb
Line: 26

Confidence: High
Category: Cross-Site Scripting
Check: CrossSiteScripting
Message: Unescaped model attribute
Code: Blog.new(blog_params).user.measurement_tag.body
File: app/views/users/blogs/show.html.erb
Line: 26

Confidence: High
Category: Format Validation
Check: ValidationRegex
Message: Insufficient validation for 'homepage' using /^https?:\/\/.*$/. Use \A and \z as anchors
File: app/models/user.rb
Line: 11

Confidence: High
Category: Redirect
Check: Redirect
Message: Possible unprotected redirect
Code: redirect_to(params[:to])
File: app/controllers/redirectors_controller.rb
Line: 4

Confidence: High
Category: SQL Injection
Check: SQL
Message: Possible SQL injection
Code: Blog.includes(:user).published.order("updated_at DESC").where("title LIKE \"%#{params[:search_text]}%\" OR body LIKE \"%#{params[:search_text]}%\"").where("created_at >= '#{params[:search_start_at]}'").where("created_at <= '#{params[:search_end_at]}'")
File: app/controllers/blogs_controller.rb
Line: 18

Confidence: High
Category: SQL Injection
Check: SQL
Message: Possible SQL injection
Code: Blog.includes(:user).published.order("updated_at DESC").where("title LIKE \"%#{params[:search_text]}%\" OR body LIKE \"%#{params[:search_text]}%\"").where("created_at >= '#{params[:search_start_at]}'")
File: app/controllers/blogs_controller.rb
Line: 14

Confidence: High
Category: SQL Injection
Check: SQL
Message: Possible SQL injection
Code: Blog.includes(:user).published.order("updated_at DESC").where("title LIKE \"%#{params[:search_text]}%\" OR body LIKE \"%#{params[:search_text]}%\"")
File: app/controllers/blogs_controller.rb
Line: 10
```

## その他の静的コード解析ツールの紹介

### [rubocop](https://github.com/rubocop-hq/rubocop)

コミュニティで管理されているスタイルガイドに準拠しているかどうかを検査する、静的コード解析ツールです。
もちろん、検査のルールのカスタマイズしたり、独自のルールを加えたりすることもできます。
これによって、ある程度形の整ったソースコードになると思います。

### [reek](https://github.com/troessner/reek)

コードのよくない匂いを検知するツールです。

### [rails_best_practices](https://github.com/flyerhzm/rails_best_practices)

[rails_best_practices](https://rails-bestpractices.com/)でよいとされている書き方から外れていないかチェックするツールです。

### [misspell](https://github.com/client9/misspell/)

英単語の綴り間違いを探すツールです。
前述のツールたちはプロジェクト全体やファイルに対して検査するのですが、
このツールを使えばプルリクエストに対してツールを適用して、
コメントを付記することができます。

### pronto

GitHubなどのプルリクエストに対して、自動コードレビューを行うためのツールです。

## サービス

* CI
  * [cider](https://sider.review/ja)
  * houndci
