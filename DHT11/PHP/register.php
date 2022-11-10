<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

require 'PDO.php' ;
$pdo = new PDOdataBase('dht11','127.0.0.1','root','' );
$myResponse = new stdClass();
$myResponse->message = "toto";
// test de connexion à la base de données
if($pdo->connect())
{
    if ( isset($_POST['Temperature']) && isset($_POST['Humidite'])) 
    {
        // on récupère les valeurs des champs du formulaire
        $Temperature = $_POST['Temperature'] ;
        $Humidite = $_POST['Humidite'] ;

        $pdo->prepare("insert into mesure values(NULL,?,?,CURRENT_TIMESTAMP)");
        $pdo->bind(1, $Temperature) ;
        $pdo->bind(2, $Humidite) ;
        if($pdo->execute())
            $myResponse->message = "OK";
        else
            $myResponse->message = $pdo->getError();
    }
    else{
        $myResponse->message = $pdo->getError();
    }
}
// on retourne la réponse    
$myJsonResponse = json_encode($myResponse);
echo $myJsonResponse ; // renvoi vers la page de login
?>