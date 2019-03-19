# HTTPとHTTPSのパケット

![パケットキャプチャー](../images/9_01_http_packet/packet_capture.png)

HTTPとHTTPSでサンプルアプリケーションにアクセスしたときに、パケットの内容が見れるのかどうかを確認します。

## お断り

筆者はパケットキャプチャツールとして、[WireShark](https://www.wireshark.org/)を使いました。
ですので、パケットキャプチャのスクリーンショットはWireSharkのものです。

## HTTP

パケットキャプチャで監視しながら、
https://localhost:3000 にアクセスしてみてください。

![HTTPで通信すると…](../images/9_01_http_packet/browser_http_get.png)

サンプルアプリケーションへのGET要求を見ると、セッションIDがそのまま見ることができます。

![パケットキャプチャでセッションIDが見える](../images/9_01_http_packet/http_packet.png)

このように、HTTPの通信は暗号化されていないので、パケットを覗き見ることで、セッションハイジャックをするために必要なセッションIDを取得することも可能です。

## HTTPS

パケットキャプチャで監視しながら、
https://localhost:9292 にアクセスしてみてください。
自己署名証明書を使っていますので、警告が出ますが、localhostへのアクセスなので、無視してアクセスしてください。

![HTTPSで通信すると…](../images/9_01_http_packet/browser_https_get.png)

通信内容を一通りみても、セッションIDどころか、どこのURLへのアクセスかもわかりません。
通信開始から終了まですべて暗号化されているためです。

![パケットキャプチャでも内容がわからない](../images/9_01_http_packet/https_packet.png)

これであれば、パケットを覗き見てセッションIDを奪うことはできなそうです。
