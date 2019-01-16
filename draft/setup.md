# サンプルアプリケーションとセットアップ

## サンプルアプリケーション

ブログを管理するWebアプリケーションです。
主な機能として、次のことができます。

* ユーザ登録
* ログイン、ログアウト
* ブログの管理（一覧、編集、削除）

## 事前に準備が必要なもの

以下のものは、すでに利用できる想定しており、インストール手順は省かせてください。

* git
* ruby
* sqlite

## セットアップ

```bash
$ git clone git@github.com:ken1flan/security_sample.git
Cloning into 'security_sample'...
remote: Enumerating objects: 556, done.
remote: Total 556 (delta 0), reused 0 (delta 0), pack-reused 556
Receiving objects: 100% (556/556), 311.77 KiB | 0 bytes/s, done.
Resolving deltas: 100% (276/276), done.
Checking connectivity... done.
$
```

```bash
$ cd security_sample/
$ bin/setup
$ bin/setup
== Installing dependencies ==
The Gemfile's dependencies are satisfied

== Preparing database ==
Created database 'db/development.sqlite3'
Created database 'db/test.sqlite3'
-- create_table("blogs", {:force=>:cascade})
   -> 0.0079s
-- create_table("measurement_tags", {:force=>:cascade})
   -> 0.0124s
-- create_table("sessions", {:force=>:cascade})
   -> 0.0267s
-- create_table("users", {:force=>:cascade})
   -> 0.0049s
-- create_table("blogs", {:force=>:cascade})
   -> 0.0062s
-- create_table("measurement_tags", {:force=>:cascade})
   -> 0.0119s
-- create_table("sessions", {:force=>:cascade})
   -> 0.0179s
-- create_table("users", {:force=>:cascade})
   -> 0.0045s

== Removing old logs and tempfiles ==

== Restarting application server ==
$
```
