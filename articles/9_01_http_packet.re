
= おまけ

== HTTPとHTTPSのパケット


//image[packet_capture][パケットキャプチャー][scale=0.5]{
//}




HTTPとHTTPSでサンプルアプリケーションにアクセスしたときに、パケットの内容が見れるのかどうかを確認します。


=== お断り


筆者はパケットキャプチャツールとして、@<href>{https://www.wireshark.org/,WireShark}を使いました。
ですので、パケットキャプチャのスクリーンショットはWireSharkのものです。
サンプルアプリケーションは自PCで起動したので、パケットの監視は、ループバックiインターフェイス、つまり自PC内の仮想的なネットワークに対して行いました。
（自身の管理しないネットワークに対して行わないでください。）


=== HTTP


https://localhost:3000 にアクセスしてみてください。



//image[browser_http_get][HTTPで通信すると…][scale=0.8]{
//}




サンプルアプリケーションへのGET要求を見ると、セッションIDがそのまま見ることができます。



//image[http_packet][パケットキャプチャでセッションIDが見える][scale=0.8]{
//}




このように、HTTPの通信は暗号化されていないので、パケットを覗き見ることで、セッションハイジャックをするために必要なセッションIDを取得することも可能です。


=== HTTPS


パケットキャプチャで監視しながら、
https://localhost:9292 にアクセスしてみてください。
自己署名証明書を使っていますので、警告が出ますが、localhostへのアクセスなので、無視してアクセスしてください。



//image[browser_https_get][HTTPSで通信すると…][scale=0.8]{
//}




通信内容を一通りみても、セッションIDどころか、どこのURLへのアクセスかもわかりません。
通信開始から終了まですべて暗号化されているためです。



//image[https_packet][パケットキャプチャでも内容がわからない][scale=0.8]{
//}




これであれば、パケットを覗き見てセッションIDを奪うことはできなそうです。

