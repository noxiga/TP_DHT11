<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

require 'PDO.php' ;
$pdo = new PDOdataBase('dht11','127.0.0.1','root','' );
$myResponse = new stdClass();

// test de connexion à la base de données
    if($pdo->connect()){
        $pdo->prepare("select * from mesure");
        if($pdo->execute())
        {
        // on prépare la réponse
            $myResponse->mesures = $pdo->resultset();
            $myResponse->message = "OK";
        }
        else
            $myResponse->message = $pdo->getError();
    }
    else
        $myResponse->message = $pdo->getError();

// on retourne la réponse    
$myJsonResponse = json_encode($myResponse);
echo $myJsonResponse ; // renvoi vers la page de login
?>