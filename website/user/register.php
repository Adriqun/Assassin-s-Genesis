<?php
  session_start();

  unset($_SESSION['error']);

  function generateRandomString($length = 30)
  {
      $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
      $charactersLength = strlen($characters);
      $randomString = '';
      for ($i = 0; $i < $length; $i++) {
          $randomString .= $characters[rand(0, $charactersLength - 1)];
      }
      return $randomString;
  }

  if(isset($_POST['email']))
  {
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

    // EMAIL
    $email = $_POST['email'];
    $email_safe = filter_var($email, FILTER_SANITIZE_EMAIL);
    if(!filter_var($email_safe, FILTER_VALIDATE_EMAIL) || $email_safe != $email)
    {
      $success = false;
      $_SESSION['e_email'] = "Valid adress email required.";
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

    // RECAPTCHA
    $mysecret = "6Lcs3GIUAAAAAG9qpx2wImGLmkhzh_KF2Y0YZrNV";
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

    // OTHER
    require_once "connect.php";
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
        $result = $connection->query("SELECT ID FROM users WHERE email='$email'");
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
        $result = $connection->query("SELECT ID FROM users WHERE username='$username'");
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

        // SUCCESS
        if( $success )
        {
          $first_time = date("d.m.Y");
          $activation_code = generateRandomString();

          if(!$connection->query("INSERT INTO usersfeatures VALUES (NULL, '$username', '@71@72@73@25@23@74', '100', '10', '0', '1', '2', '3', '4', '10', '0')"))
          {
            throw new Exception($connection->error);
          }

          if($connection->query("INSERT INTO users VALUES (NULL, '$username', '$password_hashed', '$email', '$first_time', '0', '$activation_code', 'user')"))
          {
            $_SESSION['wellregistered'] = true;
            $_SESSION['temporaryusername'] = $username;
            $_SESSION['temporaryemail'] = $email;
            $_SESSION['activation_code'] = $activation_code;
            header('Location: welcome.php');
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
  }
?>

<?php require_once("../head.php"); ?>

    <!-- NAVBAR -->
    <nav>
    <div class="nav-wrapper">
      <div class="row">
          <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
          <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
          <ul id="nav-mobile" class="right hide-on-med-and-down">
            <li><a class='nav' href='../index.php'>Start</a></li>
            <li><a class='btn nav-button' href='loginform.php'>Log In</a></li>
          </ul>
        </div>
    </div>
    </nav>
  <!-- NAVBAR MOBILE -->
    <ul class="nav-main sidenav" id="mobile-demo">
      <li><a class='nav' href='../index.php'>Start</a></li>
      <li><a class='btn nav-button' href='loginform.php'>Login In</a></li>
  </ul>
  <!-- END OF NAVBAR -->
    
    <!-- Header -->
    <div class="twelve columns">
      <section class="header" style="text-align: center; margin-top: 6em;">
        <div class="title myfont">
          <h2>Sign Up your account - Combat <span style="color: #F2583E; margin-right: 0em; margin-left: 0em; display: inline-block;">Halloween</span></h2>
        </div>
      </section>
    </div>


    <form method="post">
      <div class="row myfont">
          <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 3em;">
            <label for="exampleEmailInput" style="text-align: center;">Your username</label>
            <input class="u-full-width" type="text" placeholder="username" id="exampleEmailInput" name="username" value="<?php
          if(isset($_SESSION['rem_username']))
          {
            echo $_SESSION['rem_username'];
            unset($_SESSION['rem_username']);
          }?>">
          </div>

          <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 1em;">
            <label for="exampleEmailInput" style="text-align: center;">Your email</label>
            <input class="u-full-width" type="email" placeholder="email" id="exampleEmailInput" name="email" value="<?php
          if(isset($_SESSION['rem_email']))
          {
            echo $_SESSION['rem_email'];
            unset($_SESSION['rem_email']);
          }?>">
          </div>
      </div>

      <div class="row myfont">
          <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 1em;">
            <label for="exampleEmailInput" style="text-align: center;">Your password</label>
            <input class="u-full-width" type="password" placeholder="password" id="exampleEmailInput" name="password" value="<?php
          if(isset($_SESSION['rem_password']))
          {
            echo $_SESSION['rem_password'];
            unset($_SESSION['rem_password']);
          }?>">
          </div>

          <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 1em;">
            <label for="exampleEmailInput" style="text-align: center;">Confirm password</label>
            <input class="u-full-width" type="password" placeholder="password" id="exampleEmailInput" name="passwordcon" value="<?php
          if(isset($_SESSION['rem_passwordcon']))
          {
            echo $_SESSION['rem_passwordcon'];
            unset($_SESSION['rem_passwordcon']);
          }?>">
          </div>
        </div>

      <div class="g-recaptcha" style="margin: auto; margin-top: 1em; display: table;" data-sitekey="6Lcs3GIUAAAAAPOX9QzHOA_farHU1IKYvWrWpB-Z"></div>

      
      <div style="text-align: center; margin-top: 1em;">
        <input class="button-primary myfont" type="submit" value="Register">
      </div>
    </form>


 	     <?php
      // Errors.
      echo '<h5 class="errorColor">';
      if( isset($_SESSION['e_username']))
      {
        echo $_SESSION['e_username'];
        unset($_SESSION['e_username']);
      }
      else if( isset($_SESSION['e_email']))
      {
        echo $_SESSION['e_email'];
        unset($_SESSION['e_email']);
      }
      else if( isset($_SESSION['e_password']))
      {
        echo $_SESSION['e_password'];
        unset($_SESSION['e_password']);
      }
      else if( isset($_SESSION['e_passwordcon']))
      {
        echo $_SESSION['e_passwordcon'];
        unset($_SESSION['e_passwordcon']);
      }
      else if( isset($_SESSION['e_bot']))
      {
        echo $_SESSION['e_bot'];
        unset($_SESSION['e_bot']);
      }
      echo '</h5>';
    ?>
    
<?php require_once("../footer.php"); ?>