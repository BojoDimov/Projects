<!DOCTYPE html>
<html lang="bg">
<head>
  <title>Божидар Димов, ФН:81112, задача 1</title>
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

    function show_page($pageId, $data){
      return '<h1>'.$data[$pageId]['title'].'</h1>
        <h2>'.$data[$pageId]['lecturer'].'</h2>
        <p>'.$data[$pageId]['description'].'</p>';
    }

    echo show_page('webgl', $data);
    echo show_page('go', $data);
  ?>
</body>
</html>
