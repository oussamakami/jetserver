<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>User Information Results</title>
</head>
<body>
    <h2>Your Information:</h2>
    <?php
	parse_str(getenv('QUERY_STRING'), $_GET);
    $name = isset($_GET['name']) ? $_GET['name'] : "user didn't provide it";
    $password = isset($_GET['password']) ? $_GET['password'] : "user didn't provide it";
    $age = isset($_GET['age']) ? $_GET['age'] : "user didn't provide it";

    echo "Name: " . htmlspecialchars($name) . "<br>";
    echo "Password: " . htmlspecialchars($password) . "<br>";
    echo "Age: " . htmlspecialchars($age) . "<br>";
    ?>
</body>
</html>
