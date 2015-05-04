<?php

	error_reporting(E_ALL);
	error_reporting(-1);
	$conf['error_level'] = 2;
	ini_set('display_errors', TRUE);
	ini_set('display_startup_errors', TRUE);

	include 'lexer.php';
	include 'file.php';

	$file = new File("test/test.llm");
	$lexer = new Lexer($file);
	$lexer->startLexingFiles();

?>