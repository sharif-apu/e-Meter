
 
 <?php

//$app = new \Slim\Slim();
$app->get('/result', function () use($app){
	//echo 'hello reslut cost';
	//Query for the result
	// 1. 
    $costs=$app->db->query(
    "
    SELECT sum(watt) as user_uses from cost
    "
    )->fetchAll(PDO::FETCH_ASSOC);
	/* while ($row = $costs->fetchObject()) {
    $data[] = $row;
  } */
	
    //$test[]=$cost;
	//echo '$cost';
    $app->render('getDataView.php',[
   'totat_use' => $costs
   ]); 



//var_dump($cost);
	//die();    
	
});
