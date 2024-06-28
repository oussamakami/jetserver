<?php
// Check if form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Check if username is provided
    if (isset($_POST['username']) && !empty($_POST['username'])) {
        $username = $_POST['username'];
        echo "Username: " . htmlspecialchars($username) . "<br>";
    }

    // Check if profile picture is uploaded
    if (isset($_FILES['profile_picture']) && $_FILES['profile_picture']['error'] == UPLOAD_ERR_OK) {
        $uploadDir = './uploads/'; // Replace with your desired upload directory
        $uploadFile = $uploadDir . basename($_FILES['profile_picture']['name']);

        // Move uploaded file to specified directory
        if (move_uploaded_file($_FILES['profile_picture']['tmp_name'], $uploadFile)) {
            echo "Profile Picture uploaded successfully.<br>";
            echo '<img src="' . htmlspecialchars($uploadFile) . '" alt="Profile Picture"><br>';
        } else {
            echo "Error uploading profile picture.";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Profile Upload</title>
</head>
<body>
    <h2>Upload Username and Profile Picture</h2>
	<h4 style="color: red;">Warning: it wont work with php cli it needs php-cgi in the config file!!!</h4>
    <form method="post" enctype="multipart/form-data">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br><br>

        <label for="profile_picture">Profile Picture:</label>
        <input type="file" id="profile_picture" name="profile_picture"><br><br>

        <input type="submit" value="Submit">
    </form>
</body>
</html>
