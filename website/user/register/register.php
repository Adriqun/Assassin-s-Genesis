<?php
	// Start session.
	session_start();

	// Just in case.
	unset($_SESSION['error']);

	require_once("../other/generateCode.php");

	function backToRegisterForm()
	{
		header('Location: registerform.php');
		exit();
	}

	// Status.
	$success = true;

	// USERNAME
	$username = $_POST['username'];
	if((strlen($username)) < 4)
	{
		$success = false;
		$_SESSION['e_username'] = "Please choose a name with at least 4 characters.";
	}
	else if((strlen($username)) > 12)
	{
		$success = false;
		$_SESSION['e_username'] = "Maximum number of chars is 12.";
	}
	else if(!ctype_alnum($username))
	{
		$success = false;
		$_SESSION['e_username'] = "This name is unavailable.";
	}

	// PASSWORD
	$password = $_POST['password'];
	$passwordcon = $_POST['passwordcon'];
	if((strlen($password)) < 8)
	{
		$success = false;
		$_SESSION['e_password'] = "Please choose a password with at least 8 characters.";
	}
	else if((strlen($password)) > 20)
	{
		$success = false;
		$_SESSION['e_password'] = "Password may contain at the maximum 20 characters.";
	}
	else if($password != $passwordcon)
	{
		$success = false;
		$_SESSION['e_passwordcon'] = "Passwords do not match.";
	}
	$password_hashed = password_hash($password, PASSWORD_DEFAULT);

	// EMAIL
	$email = $_POST['email'];
	$email_safe = filter_var($email, FILTER_SANITIZE_EMAIL);
	if(!filter_var($email_safe, FILTER_VALIDATE_EMAIL) || $email_safe != $email)
	{
		$success = false;
		$_SESSION['e_email'] = "Valid address email required.";
	}

	// RECAPTCHA
	$mysecret = "6Lf9NWgUAAAAAAe-lNJAcxTOubIdu_KUe-cSMwTU";
	$confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
	if(!json_decode($confirm)->success)
	{
		$success = false;
		$_SESSION['e_bot'] = "Confirm humanity.";
	}

	// REMEMBER DATA
	$_SESSION['rem_username'] = $username;
	$_SESSION['rem_email'] = $email;
	$_SESSION['rem_password'] = $password;
	$_SESSION['rem_passwordcon'] = $passwordcon;

	if(!$success) backToRegisterForm();

	require_once ("../../connect.php");

	mysqli_report(MYSQLI_REPORT_STRICT);

	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
		{
			throw new Exception(mysqli_connect_errno());
		}
		else
		{
			// IF EMAIL EXIST
			$result = $connection->query(sprintf("SELECT ID FROM users WHERE email='%s'", mysqli_real_escape_string($connection, $email)));
			if(!$result)
			{
				throw new Exception($connection->error);
			}
			$how_many_emails = $result->num_rows;
			if($how_many_emails > 0)
			{
				$success = false;
				$_SESSION['e_email'] = "This email already exists.";
			}

			// IF USERNAME EXISTS
			$result = $connection->query(sprintf("SELECT ID FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $username)));
			if(!$result)
			{
				throw new Exception($connection->error);
			}
			$how_many_usernames = $result->num_rows;
			if($how_many_usernames > 0)
			{
				$success = false;
				$_SESSION['e_username'] = "This username already exists.";
			}

			if(!$success)
				backToRegisterForm();

			// SUCCESS
			if($success)
			{
				$first_time = date("d.m.Y");
				$activation_code = generateCode();

				$heart_points = 20;
				$magic_points = 10;
				$armour = 50;			// 0 ... 1000
				$magic_resistant = 25;	// 0 ... 1000
				$movement_speed = 25;	// 0 ... 100
				$damage = 4;
				$magic_damage = 2;
				$luck = rand(2, 49);	// 0 ... 50
				$experience = 0;		// 0 ... 100
				$level = 1;

				$sql_query = "INSERT INTO usersfeatures VALUES (NULL, '$username', '71@72@73@23@25@', '$heart_points', '$magic_points', '$armour', '$magic_resistant', '$movement_speed', '$damage', '$magic_damage', '$luck', '$experience', '$level')";
				if(!$connection->query($sql_query))
				{
					throw new Exception($connection->error);
				}

				$sql_query = "INSERT INTO users VALUES (NULL, '$username', '$password_hashed', '$email', '$first_time', '0', '$activation_code', 'user')";
				if($connection->query($sql_query))
				{
					$_SESSION['wellregistered'] = true;
					$_SESSION['activation_code'] = $activation_code;
					header('Location: ../other/welcome.php');
					exit();
				}
				else
				{
					throw new Exception($connection->error);
				}
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}
?>