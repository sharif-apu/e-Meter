<?php

//$app = new \Slim\Slim();

$app->post('/cost_update', function() use ($app) {
            // check for required params
            //verifyRequiredParams(array('name', 'email', 'password'));

           // $response = array();

            // reading post params
            $use = $app->request->post('watt');
            $time = $app->request->post('sec');
            $senID = $app->request->post('senID');
			$sql = "insert into cost (watt, sec, senID ) values ('$use','$time','$senID')";
	try{
	 $cost=$app->db->query($sql)->fetchAll(PDO::FETCH_ASSOC);
    echo 'Successfull!!!';
    var_dump($cost);
    die(); 	
		
	}
	catch(PDOException $e){
	echo 'Not Successfull!!';
	}

        
        });


/* $app->get('/cost', function () use($app){
	echo 'hello reslut cost';
	//Query for the result
	// 1. 
	
   
	
	
	
}); */

