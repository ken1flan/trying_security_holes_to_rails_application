# SQLインジェクション

## SQLインジェクションとは？

### 埋め込みやすい状況

## SQLインジェクションを試す

### ブログの検索

ブログ一覧を開く
http://localhost:3000/blogs

このページは、登録されているブログをキーワードなどで検索できる機能があります。
検索ワードに`cat`などの任意のキーワードを入れて、`Search`ボタンを押すと、そのキーワードが含まれるブログが表示されます。

ブログには`draft`、いわゆる下書きという状態があり、この状態のときには他のユーザには見えないようになっています。
なので、検索しても`draft`の記事は出てきません。

![Search blogs with keyword 'cat'](https://cdn-ak.f.st-hatena.com/images/fotolife/k/ken1flan/20190120/20190120201052.png)

### 特殊なキーワードで検索

テキスト検索のところに `%") OR 1=1 OR (title LIKE "` を入れて Search ボタンを押します。

そうすると、`draft`のバッジのついたブログが混じっています。

![Search blogs with SQL injection](https://cdn-ak.f.st-hatena.com/images/fotolife/k/ken1flan/20190120/20190120201524.png)

タイトルまたは本文内を指定されたキーワードで検索するSQLを考えてみます。

```sql
SELECT
  *
FROM blogs
WHERE (title LIKE "%指定のキーワード%" OR body LIKE "%指定のキーワード%")
AND status = 1;
```

キーワードに`%") OR 1=1 OR (title LIKE "`を入れてみると…。

```sql
SELECT
  *
FROM blogs
WHERE (title LIKE "%%") OR 1=1 OR (title LIKE "%" OR body LIKE "%%") OR 1=1 OR (title LIKE "%")
AND status = 1;
```

`1=1`という絶対成立する条件が挟み込まれて、すべてのデータが表示されてしまいました。

## 直し方

