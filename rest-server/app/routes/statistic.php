
 
 <?php

//$app = new \Slim\Slim();
$app->get('/statistic', function () use($app){
	//echo 'hello reslut cost';
	//Query for the result
	// 1. 
    $result=$app->db->query(
    "
    SELECT date(update_time) as Date, sum(watt)/1000 as Uses from cost group by date(update_time)
    "
    )->fetchAll(PDO::FETCH_ASSOC);
	/* while ($row = $costs->fetchObject()) {
    $data[] = $row;
  } */
	
    //$test[]=$cost;
	//echo '$cost';
   /* $app->render('statistic.php',[
   'stat' => $status
   ]); 
  */
  header("Content-Type: application/json");
echo json_encode($result);
exit;


//var_dump($cost);
	//die();    
	
});
