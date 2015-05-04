<?php

	class File {

		private $fileName;
		private $fileContents;
		private $fileHandle;

		public function __construct($fileName) {
			$this->fileName = $fileName;
			$this->fileHandle = fopen($fileName, "r");
			if ($this->fileHandle) {
				while (($line = fgets($this->fileHandle)) !== false) {
					$this->fileContents .= $line . "\n";
				}
				fclose($this->fileHandle);
			}
		}

		public function getFileName() {
			return $this->fileName;
		}

		public function getFileContents() {
			return $this->fileContents;
		}

		public function getFileHandle() {
			return $this->fileHandle;
		}

	}

?>