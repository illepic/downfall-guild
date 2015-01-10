<?
/***********************************************************************************
 *
 *   lua2php_array - Converts an WoW-Lua File into a php-Array.
 *
 *   Author: PattyPur (Patty.Pur@web.de)
 *   Char : Shindara 
 *   Guild: Ehrengarde von Theramore
 *   Realm: Kel'Thuzad (DE-PVP)
 *   
 *   Date: 02.10.2005
 *
 **********************************************************************************
 */

// Helper-functions

/*
  function trimval(string)
  
  cuts the leading and tailing quotationmarks and the tailing comma from the value
  Example:
    Input: "Value",
    Output: Value    
*/
function trimval($str)
{
  $str = trim($str);
  if (substr($str,0,1)=="\""){
    
    $str  = trim(substr($str,1,strlen($str)));
  }
  if (substr($str,-1,1)==","){
    $str  = trim(substr($str,0,strlen($str)-1));
  }

  if (substr($str,-1,1)=="\""){
    $str  = trim(substr($str,0,strlen($str)-1));
  }
  
  if ($str =='false') 
  {
    $str = false;
  }
  if ($str =='true') 
  {
    $str = true;
  }
  
  return $str;
}

/*
  function array_id(string)
  
  extracts the Key-Value for array indexing 
  String-Example:
    Input: ["Key"]
    Output: Key    
  Int-Example:
    Input: [0]
    Output: 0    
*/
function array_id($str)
{
  $id1 = sscanf($str, "[%d]");  
  if (strlen($id1[0])>0){
    return $id1[0];    
  }
  else
  {
    if (substr($str,0,1)=="[")
    {
      $str  = substr($str,1,strlen($str));
    }
    if (substr($str,0,1)=="\"")
    {
      $str  = substr($str,1,strlen($str));
    }
    if (substr($str,-1,1)=="]")
    {
      $str  = substr($str,0,strlen($str)-1);
    }
    if (substr($str,-1,1)=="\"")
    {
      $str  = substr($str,0,strlen($str)-1);
    }
    return $str;
  }
}

/*
  function luaparser(array, arrayStartIndex)
  
  recursive Function - it does the main work
*/
function luaparser($lua, &$pos)
{
  $parray = array();
  $stop = false;
  if ($pos < count($lua))
  {
    for ($i = $pos;$stop ==false;)
    {
       if ($i >= count($lua)-1) { $stop=true;}
       $strs = explode("=",utf8_decode($lua[$i]));
       if (isset($strs[1]) && (trim($strs[1]) == "{")) {
         $i++;
         $parray[array_id(trim($strs[0]))]=luaparser($lua, $i);
       }
       else if (trim($strs[0]) == "{")
       {
         $i++;
         $temp = array();
         $temp = luaparser($lua, $i);
         $vkey = array_id(trim(substr(trim($lua[$i-1]), 5)));
         $parray[$vkey] = $temp;
       }
       // ||
       else if (trim($strs[0]) == "}" ||  trim($strs[0]) == "}," || substr(trim($strs[0]), 0, 2) == "},")
       {
         //$i--;
         $i++;
         $stop = true;
       }
       else
       {
         $i++;
         if ((isset($strs[1])) && (strlen(array_id(trim($strs[0])))>0 && strlen($strs[1])>0))
         {
           $parray[array_id(trim($strs[0]))]=trimval($strs[1]);
         }
       }
      }
  }
  $pos=$i;
  return $parray;
}

/*
  function makePhpArray($input)
  
  thst the thing to call :-)
  
  $input can be 
    - an array with the lines of the LuaFile
    - a String with the whole LuaFile
    - a Filename
  
*/
function makePhpArray($input){
  $start = 0;
  if (is_array($input))
  {    
    return luaparser($input,$start);
  } 
  elseif (is_string($input))
  {
    if (is_file ( $input ))
    {
	$handle = fopen($input,"r");
	$inputstring = fread($handle, filesize($input));
	//$inputstring = file($input);
	$inputstring = str_replace("'", "", $inputstring);
	$inputstring = str_replace("á", "'a", $inputstring);
	$inputstring = str_replace("é", "'e", $inputstring);
	$inputstring = str_replace("ö", ":o", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 4", "[\"Slots\"] = \"4\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 6", "[\"Slots\"] = \"6\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 8", "[\"Slots\"] = \"8\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 10", "[\"Slots\"] = \"10\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 12", "[\"Slots\"] = \"12\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 14", "[\"Slots\"] = \"14\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 16", "[\"Slots\"] = \"16\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 18", "[\"Slots\"] = \"18\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 20", "[\"Slots\"] = \"20\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 22", "[\"Slots\"] = \"22\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 24", "[\"Slots\"] = \"24\"", $inputstring);
	$inputstring = str_replace("[\"Slots\"] = 26", "[\"Slots\"] = \"26\"", $inputstring);
    //echo $inputstring;
    return luaparser(explode("\n",$inputstring),$start);
      //return luaparser($inputstring,$start);
    }
    else
    {
      return luaparser(explode("\n",$input),$start);
    }
  }  
}
?>
