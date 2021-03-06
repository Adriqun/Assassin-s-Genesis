<?php

	session_start();

	require_once("../../user/login/isLogged.php");

	require_once("../../user/other/isModerator.php");

	require_once("../../common/head.php");
?>
	
	<!-- NAVBAR -->
	<?php require_once("../../common/navbar-b.php"); ?>
				<li><a class="btn-floating btn-medium pulse blue lighten-1" href="../../home.php"><i class="material-icons">home</i></a></li>
				<li><a class="nav btn white japokki-black" href="../index.php">Back</a></li>
	<?php require_once("../../common/navbar-e.php"); ?>
	<?php require_once("../../common/sidenav-b.php"); ?>
		<li><a class="japokki-black" href="../../home.php"><i class="material-icons">home</i>Home</a></li>
		<li><a class="japokki-black" href="../index.php"><i class="material-icons">arrow_back</i>Back</a></li>
	<?php require_once("../../common/sidenav-e.php"); ?>
	<!-- END OF NAVBAR -->

<div class="container center">
	<div class="row">
		<h2 class="japokki-black A22">About Modules</h2>
		<h4 class="japokki-black A4">The module is a part of the application that has its own life during program execution. We divide application because only then it's easier to find a single bug. During testing try to do anything that's in your mind, try to crash the application, make undefined behavior, anything you like. Our method of making the application better is a spiral method. We upload module, the module is being tested, any errors are caught and added into the bug list, the module is updated and the loop starts again. Also, we work with agile software development, we don't have one single deadline for the project, we do small tasks and small updates so at the end, we have a final product. Please check out current modules and try to find bugs. Ascribe new bug to devmichalek@gmail.com.</h4>

		<h2 class="japokki-black A22">List Of <a target="_blank" href="https://drive.google.com/drive/folders/11UgUFJxFb2fVNwL4eFe3pMbAtwE80hTQ">Modules</a></h2>
		<h4 class="japokki-black A4">Map Editor (add/edit/remove map) Update(-) - Download</h4>
		<h4 class="japokki-black A4">Introduction (1st scene, intro, logging system) Update(2018.07.26) Release(Windowsx86) - <a target="_blank" href="https://drive.google.com/uc?authuser=0&id=1m8xQxcSJJ-euS28D4y6433tkWuR44iVt&export=download">Download</a></h4>
		<h4 class="japokki-black A4">Menu (2nd scene, main menu) Update(-) Release(-) - Download</h4>
		<h4 class="japokki-black A4">Level Menu (3rd scene, level menu, chosing level) Update(-) - Download</h4>
		<h4 class="japokki-black A4">Platform (4th scene, that's where game starts ) Update(-) - Download</h4>
		<h4 class="japokki-black A4">End Scene (5th scene, user died etc., shows stats) Update(-) - Download</h4>
	</div>
</div>

<?php require_once("../../common/footer.php"); ?>