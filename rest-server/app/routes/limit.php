<?php
$app->get('/limit', function ()use($app) {
   // echo "Hello, $name,$abc";
	//$sql = "insert into cost (watt, time, senID ) values ('$watt','$time','$senID')";
	try{
	
    $cost=$app->db->query(
    "
    SELECT maxUse from user_info
    "
    )->fetchAll(PDO::FETCH_ASSOC);
    
   $app->render('getLimitView.php',[
	
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