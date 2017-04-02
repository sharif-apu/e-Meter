<?php
$app->get('/statusUpdate/:devID/:status', function ($devID,$status)use($app) {
   // echo "Hello, $name,$abc";
   if($devID ==1){
	  
	  try{
	 $sql = "update user_info set dev1=$status where id=1111";
	 $app->db->query($sql)->fetchAll(PDO::FETCH_ASSOC);
	 echo 'Device status Updated1';
	}
	catch(PDOException $e){
	echo 'Not Successfull!!';
	} 
	   
   }
else if($devID==2){
	
	try{
	 $sql = "update user_info set dev2=$status where id=1111";
	 $app->db->query($sql)->fetchAll(PDO::FETCH_ASSOC);
	 echo 'Device status Updated';
	}
	catch(PDOException $e){
	echo 'Not Successfull!!';
	} 
	
	
}
	 
});