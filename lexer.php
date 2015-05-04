<?php

	class Lexer {

		private $files;
		private $numOfFiles;

		public function __construct($file) {
			$this->files = array(
				$file
			);
			$this->numOfFiles = count($this->files);
		}

		public function lexFile($file) {
			echo "<p>" . str_replace("\n", "</p></p>", $file->getFileContents()) . "</p>";
		}

		public function startLexingFiles() {
			for ($i = 0; $i < $this->numOfFiles; $i++) {
				$this->lexFile($this->files[$i]);
			}
		}

	}

?>