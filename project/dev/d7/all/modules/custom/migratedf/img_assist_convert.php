<?php
$prefix = 'demo_';
$server = "localhost";
$login = "root";
$password = "root";
$database = "downfall";

///////////////////////////////////////////////////////////////////////////////////////////////////

$link = mysql_connect($server, $login, $password) or die("Connect error : " . mysql_error());
echo "Connect OK\n";

$db_selected = mysql_select_db($database, $link);
if (!$db_selected)
   die ('Select DB error : ' . mysql_error());

$query = "SELECT * FROM " . $prefix . "field_data_body WHERE body_value like '%[img_assist%'";
$result = mysql_query($query);

if (!$result) {
    $message  = 'Query error : ' . mysql_error() . "\n";
    $message .= 'Query : ' . $query;
    die($message);
}

$count=0;
while ($row = mysql_fetch_assoc($result))
{
    $tmp = $row['body_value'];
    $count++;
    echo "\n###############################################################################\n";
    echo "Entity ID: ".$row['entity_id'];
    //echo $tmp;
    //echo "\n###############################################################################\n";

    $start = strpos($tmp, "[img_assist");

    while (($start = strpos($tmp, "[img_assist")) !== FALSE) // Added parentheses here since operator precedence was incorrect.
    {
        $end = strpos($tmp, "]", $start);
        $img = substr($tmp, $start+12, $end-$start-12);

        echo "Img: $img \n";

        list($nid, $title, $desc, $link_img, $align, $width, $height) = explode("|", $img);

        $nid = substr($nid, strpos($nid, "=")+1);
        $title = substr($title, strpos($title, "=")+1);
        $desc = substr($desc, strpos($desc, "=")+1);
        $link_img = substr($link_img, strpos($link_img, "=")+1);
        $align = substr($align, strpos($align, "=")+1);
        $width = substr($width, strpos($width, "=")+1);
        $height = substr($height, strpos($height, "=")+1);

        echo "NID: $nid \n";

        $query_image = "SELECT * FROM " . $prefix . "image WHERE nid=".$nid . " and image_size = '_original'"; // Changed query to always get the original image. Formerly, the query would return a row for each derivative of the image such as thumbnail.
        $result_image = mysql_query($query_image);

        $row_image = mysql_fetch_assoc($result_image);
        $fid = $row_image['fid'];

        echo "FID: $fid \n";

        $query_file = "SELECT * FROM " . $prefix . "files WHERE fid=".$fid;
        $result_file = mysql_query($query_file);

        $row_file = mysql_fetch_assoc($result_file);
        $img_path = $row_file['filepath'];

        if ($img_path[0] != '/')
            $img_path = '/' . $img_path;

        echo "Src: $img_path \n";

        $buffer = substr($tmp, 0, $start);

        $buffer .= "<a class=\"img-full\" href=\"$img_path\"><img alt=\"$desc\" src=\"$img_path\" width=\"$width\" height=\"$height\" class=\"inline inline-$align\" /></a>"; // Not a critical change, but now specifies width and height in the image's attribute tags. Also preserves the alignment of the image if the user specified an alignment through image assist.

        $buffer .= substr($tmp, $end+1);

        //echo "Buffer: $buffer \n";

        $tmp = $buffer;

        mysql_free_result($result_image);
        //break; // Test
    } // End : while ($start = strpos($tmp, "[img_assist"))

    $update_query = "UPDATE " . $prefix . "field_data_body SET body_value = '".addslashes($tmp)."' WHERE entity_id = ".$row['entity_id'];
    $res = mysql_query($update_query);

    if (!$res) {
        $message  = 'Query error : ' . mysql_error() . "\n";
        $message .= 'Query : ' . $update_query;
        die($message);
    }

    //break; // Test
}// End : while ($row = mysql_fetch_assoc($result))


/* =================== COMMENTS ==================== */
// do the same for comments as for main nodes

$query = "SELECT * FROM " . $prefix . "field_data_comment_body WHERE comment_body_value like '%[img_assist%'";
$result = mysql_query($query);

if (!$result) {
    $message  = 'Query error : ' . mysql_error() . "\n";
    $message .= 'Query : ' . $query;
    die($message);
}

$count=0;
while ($row = mysql_fetch_assoc($result))
{
    $tmp = $row['comment_body_value'];
    $count++;
    echo "\n###############################################################################\n";
    echo "Entity ID: ".$row['entity_id'];
    //echo $tmp;
    //echo "\n###############################################################################\n";

    $start = strpos($tmp, "[img_assist");

    while (($start = strpos($tmp, "[img_assist")) !== FALSE) // Added parentheses here since operator precedence was incorrect.
    {
        $end = strpos($tmp, "]", $start);
        $img = substr($tmp, $start+12, $end-$start-12);

        echo "Img: $img \n";

        list($nid, $title, $desc, $link_img, $align, $width, $height) = explode("|", $img);

        $nid = substr($nid, strpos($nid, "=")+1);
        $title = substr($title, strpos($title, "=")+1);
        $desc = substr($desc, strpos($desc, "=")+1);
        $link_img = substr($link_img, strpos($link_img, "=")+1);
        $align = substr($align, strpos($align, "=")+1);
        $width = substr($width, strpos($width, "=")+1);
        $height = substr($height, strpos($height, "=")+1);

        echo "NID: $nid \n";

        $query_image = "SELECT * FROM " . $prefix . "image WHERE nid=".$nid . " and image_size = '_original'"; // Changed query to always get the original image. Formerly, the query would return a row for each derivative of the image such as thumbnail.
        $result_image = mysql_query($query_image);

        $row_image = mysql_fetch_assoc($result_image);
        $fid = $row_image['fid'];

        echo "FID: $fid \n";

        $query_file = "SELECT * FROM " . $prefix . "files WHERE fid=".$fid;
        $result_file = mysql_query($query_file);

        $row_file = mysql_fetch_assoc($result_file);
        $img_path = $row_file['filepath'];

        if ($img_path[0] != '/')
            $img_path = '/' . $img_path;

        echo "Src: $img_path \n";

        $buffer = substr($tmp, 0, $start);

        $buffer .= "<a class=\"img-full\" href=\"$img_path\"><img alt=\"$desc\" src=\"$img_path\" width=\"$width\" height=\"$height\" class=\"inline inline-$align\" /></a>"; // Not a critical change, but now specifies width and height in the image's attribute tags. Also preserves the alignment of the image if the user specified an alignment through image assist.

        $buffer .= substr($tmp, $end+1);

        //echo "Buffer: $buffer \n";

        $tmp = $buffer;

        mysql_free_result($result_image);
        //break; // Test
    } // End : while ($start = strpos($tmp, "[img_assist"))

    $update_query = "UPDATE " . $prefix . "field_data_comment_body SET comment_body_value = '".addslashes($tmp)."' WHERE entity_id = ".$row['entity_id'];
    $res = mysql_query($update_query);

    if (!$res) {
        $message  = 'Query error : ' . mysql_error() . "\n";
        $message .= 'Query : ' . $update_query;
        die($message);
    }

    //break; // Test
}// End : while ($row = mysql_fetch_assoc($result))


mysql_free_result($result);

mysql_close($link);
echo "\nEnd ($count entities modified)\n\n";
?>