<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>GET Method Test - PHP Process</title>
</head>
<body>
    <h2>Received Data:</h2>
    <?php
	parse_str(getenv('QUERY_STRING'), $_GET);
    if (isset($_GET['name'])) {
        $name = htmlspecialchars($_GET['name']);
        echo "<p>Hello, $name!</p>";
    } else {
        echo "<p>No name received.</p>";
    }
    ?>
</body>
</html>
