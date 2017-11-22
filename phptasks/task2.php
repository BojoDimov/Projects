<!DOCTYPE html>
<html lang="bg">
<head>
  <meta charset="UTF-8">
  <title>Божидар Димов, ФН:81112, задача 2</title>
</head>
<body>
  <?php
    $data = array(
      'webgl' => array(
        'title' => 'Компютърна графика с WebGL',
        'description' => '...',
        'lecturer' => 'доц. П. Бойчев',
      ),
      'go' => array(
        'title' => 'Програмиране с Go',
        'description' => '...',
        'lecturer' => 'Николай Бачийски',
      )
    );

    function show_nav($data, $pageId){
      $result = '<nav>';
      foreach($data as $course => $info){
        $result = $result.'<a href="?page=' . $course . ($course == $pageId ? '" class="selected">' : '">') . $info['title'].'</a>';
        // $result = $result.'<a href="">' . $info['title'] . '</a>';
      }

      $result = $result . '</nav>';

      return $result;
    }

    echo show_nav($data, 'webgl');
  ?>
  
</body>
</html>