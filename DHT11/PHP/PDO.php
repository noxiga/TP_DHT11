<?php
class PDOdataBase {
    private $dbName ;
    private $dbHost ;
    private $dbUsername ;
    private $dbUserPassword ;
    private $handler = null ;
    private $error="" ;
    private $stmt ;


    public function __construct($dbName ,$dbHost, $dbUsername, $dbUserPassword ) {
        $this->dbName = $dbName;
        $this->dbHost = $dbHost;
        $this->dbUsername = $dbUsername;
        $this->dbUserPassword = $dbUserPassword;
    }


    public function connect() {
        if ( null == $this->handler ) {
            try{
                $this->handler = new PDO("mysql:host=".$this->dbHost. ";" . "dbname=". $this->dbName . ";charset=utf8",$this->dbUsername,$this->dbUserPassword);
                $this->handler->setAttribute(PDO::ATTR_ERRMODE,
                PDO::ERRMODE_EXCEPTION);
                return true ; // réussite de la connexion
            }
            catch(PDOException $e) {
                $this->error =$e->getMessage();
                return false ; // echec à la connexion
            }
        }
    }

    public function getError() {
        return $this->error ;
    }

    public function disconnect() {
        $this->handler = null;
    }

    //The query method also introduces the PDO::prepare function.
    public function prepare($query){
    $this->stmt = $this->handler->prepare($query);
    }

    //Param is the placeholder value that we will be using in our SQL statement, example :name.
    //Value is the actual value that we want to bind to the placeholder, example “John Smith”.
    //Type is the datatype of the parameter, example string.
    public function bind($param, $value, $type = null) {
        if (is_null($type)) {
            switch (true) {
                case is_int($value):
                    $type = PDO::PARAM_INT;
                    break;
                case is_bool($value):
                    $type = PDO::PARAM_BOOL;
                    break;
                case is_null($value):
                    $type = PDO::PARAM_NULL;
                    break;
                default:
                    $type = PDO::PARAM_STR;
            }
        }
        $this->stmt->bindValue($param, $value, $type);
    }

    //The next method we will be look at is the PDOStatement::execute
    public function execute(){
    // try .... catch pour le cas fréquent où la requête SQL n'est pas correcte
    try{
        return $this->stmt->execute();
        }
        catch(PDOException $e) {
            $this->error = $e->getMessage();
        }
    }

    //The Result Set function returns an array of the result set rows.
    public function resultset(){
        return $this->stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    //Very similar to the previous method, the Single method simply returns a single record from the database
    public function single(){
        return $this->stmt->fetch(PDO::FETCH_ASSOC);
    }

    //the next method simply returns the number of effected rows from the previous delete, update or insert statement.
    public function rowCount(){
        return $this->stmt->rowCount();
    }

    //The Last Insert Id method returns the last inserted Id as a string.
    public function lastInsertId(){
        return $this->handler->lastInsertId();
    }

    //To begin a transaction:
    public function beginTransaction(){
        return $this->handler->beginTransaction();
    }

    //to end a transaction and commit your changes:
    public function endTransaction(){
        return $this->handler->commit();
    }
    //The Debut Dump Parameters methods dumps the the information that was contained in the Prepared Statement
    public function debugDumpParams(){
        return $this->stmt->debugDumpParams();
    }
}
?>