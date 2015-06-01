# LLM
LLM is a prototype language I'm writing to replace PHP for some of my
personal projects.

# Example
![amazing..](http://i.imgur.com/UCcafLs.png)
You can go and see for yourself [here](http://llm.felixangell.com/)!

# Building
First you need to compile by running make:

    $ make

Then you need to start your web server (in this case nginx):

    # mac
    $ sudo nginx

    # linux
    $ sudo service nginx start

Finally, you can spawn the fcgi process, and check it out on
`localhost:3321` (or whatever port you set nginx/fcgi to use).

    $ make spawn

You can press `ctrl+c` to stop the process.

# Dependencies

* fcgi c++ library
* spawn-fcgi
* fcgi
* nginx
* clang++/g++/...

# Setup

I'm using nginx with the following configuration:

    worker_processes  1;

    events {
        worker_connections 1024;
    }

    http {
        server {
            listen 3321;
            server_name localhost;

            location / {
                fastcgi_pass   127.0.0.1:8000;
                fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
                fastcgi_param  SERVER_SOFTWARE    nginx;
                fastcgi_param  QUERY_STRING       $query_string;
                fastcgi_param  REQUEST_METHOD     $request_method;
                fastcgi_param  CONTENT_TYPE       $content_type;
                fastcgi_param  CONTENT_LENGTH     $content_length;
                fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
                fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
                fastcgi_param  REQUEST_URI        $request_uri;
                fastcgi_param  DOCUMENT_URI       $document_uri;
                fastcgi_param  DOCUMENT_ROOT      $document_root;
                fastcgi_param  SERVER_PROTOCOL    $server_protocol;
                fastcgi_param  REMOTE_ADDR        $remote_addr;
                fastcgi_param  REMOTE_PORT        $remote_port;
                fastcgi_param  SERVER_ADDR        $server_addr;
                fastcgi_param  SERVER_PORT        $server_port;
                fastcgi_param  SERVER_NAME        $server_name;
            }
        }
    }