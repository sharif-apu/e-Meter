<?php
$app->get('/arddata/:watt/:time/:senID', function ($watt,$time,$senID)use($app) {
   // echo "Hello, $name,$abc";
	$sql = "insert into cost (watt, time, senID ) values ('$watt','$time','$senID')";
	try{
	 $insert=$app->db->query($sql)->fetchAll(PDO::FETCH_ASSOC);
	 $sql= "select watt from cost";
	 //$cost=$app->db->query($sql)->fetchAll(PDO::FETCH_ASSOC);
    $cost=$app->db->query(
    "
    SELECT sum(watt)/1000 as user_uses from cost
    "
    )->fetchAll(PDO::FETCH_ASSOC);
    
   $app->render('getDataView.php',[
	
	'totat_use' =>$cost
	]);  
	/* echo '$cost';
	var_dump($cost);
	die(); */
		
	}
	catch(PDOException $e){
	echo 'Not Successfull!!';
	}
});