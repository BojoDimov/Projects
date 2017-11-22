<!DOCTYPE html>
<html lang="bg">
<head>
  <meta charset="UTF-8">
  <title>Божидар Димов, ФН:81112, задача 3</title>
</head>
<body>
  <?php

    function pretify($what){
      return '<span style="display:block">'.$what.'</span>';
    }

    class Request{
      protected $server = array();
      
      function __construct($SERVER){
        $this->server = $SERVER;
      }
      
      public function getMethod(){
        return strtolower($this->server['REQUEST_METHOD']);
      }

      public function getPath(){
        return isset($this->server['PATH_INFO']) ? $this->server['PATH_INFO'] : '';
      }

      public function getURL(){
        return $this->server['SERVER_NAME'].':'.$this->server['SERVER_PORT'].$this->server['REQUEST_URI'];
      }

      public function getUserAgent(){
        return $this->server['HTTP_USER_AGENT'];
      }
    }

    class GetRequest extends Request{
      public function getData(){
        if(strlen($this->server['QUERY_STRING']) == 0) return '{}';
        return '{"'.str_replace('&', '","', str_replace('=', '":"', $this->server['QUERY_STRING'])).'"}';
      }
    }

    $request = new Request($_SERVER);
    $get_req = new GetRequest($_SERVER);
    echo pretify($request->getMethod());
    echo pretify($request->getPath());
    echo pretify($request->getURL());
    echo pretify($request->getUserAgent());
    echo pretify($get_req->getData());
  ?>
  
</body>
</html>