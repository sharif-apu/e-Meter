
 
 <?php

//$app = new \Slim\Slim();
$app->get('/sensorData', function () use($app){
	//echo 'hello reslut cost';
	//Query for the result
	// 1. 
    $status=$app->db->query(
    "
    SELECT concat(dev1,dev2) as divStatus from user_info where id=1111
    "
    )->fetchAll(PDO::FETCH_ASSOC);
	/* while ($row = $costs->fetchObject()) {
    $data[] = $row;
  } */
	
    //$test[]=$cost;
	//echo '$cost';
    $app->render('getSensorDataView.php',[
   'totat_use' => $status
   ]); 



//var_dump($cost);
	//die();    
	
});
