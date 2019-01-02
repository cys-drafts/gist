#!/bin/bash

exec 3<>/dev/tcp/www.baidu.com/80
echo -e 'GET / HTTP/1.1\r\nConnection: close\r\n\r\n' >&3
cat <&3
exec 3>&-
