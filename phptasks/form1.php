<?php
  $form = array(
    "courseName" => array(
      "pred" => validate_len(150),
      "error" => "Course Name exceeds MAX symbols limit! (limit is 150 symbols)"
    ),
    "lecturerName" => array(
      "pred" => validate_len(200),
      "error" => "Lecturer name exceeds MAX symbols limit! (limit is 200 symbols)"
    ),
    "description" => array(
      "pred" => validate_len(10),
      "error" => "Description exceeds MAX symbols limit! (limit is 10 symbols)"
    ),
    "group" => array(
      "pred" => function($item){ return (int)$item >= 1 && (int)$item <= 4; },
      "error" => "Group must be one of  М, ПМ, ОКН, ЯКН"
    ),
    "credits" => array(
      "pred" => function($item){ return (int)$item > 0 && (float)((int)$item) == (float)$item; },
      "error" => "Credits must be natural number;" 
    )
  );

  $valid = true;

  foreach($form as $key => $value){
    if(!$value["pred"]($_POST[$key])){
      $valid = false;
      echo '<span style="display:block;">'.$value["error"].'</span>';
    }
  }

  if($valid){
    echo '<span>Form is valid.</span>';
  }

  function validate_len($len){
    return function($item) use ($len) { return $item < $len; };
  }
?>