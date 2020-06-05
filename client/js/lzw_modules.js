angular.module('LZW', ['myAppControllers', 'myAppServices'] );

var myAppControllers = angular.module('myAppControllers', []);

myAppControllers.controller('codeController',
	['$scope', 'srvInfo',
		function ($scope, srvInfo) {

		$scope.isCoding = Boolean(true);
		$scope.bitSizes = [ {code: 9, name: '9'}, {code: 10, name: '10'}, {code: 11, name: '11'},
							{code: 12, name: '12'}, {code: 13, name: '13'}, {code: 14, name: '14'},
							{code: 15, name: '15'}, {code: 16, name: '16'} ];
		$scope.compressionRate = 0.0;

		$scope.run = function(data) {
			if ($scope.isCoding) {
				srvInfo.encode(
					function(data) {
						$scope.outcode = data.data.code;
					});
			}
			else {
				srvInfo.decode(
					function(data) {
						$scope.outcode = data.data.text;
					});
			}
			srvInfo.getCompressionRate(
				function(data) {
					$scope.compressionRate = data.data.CR.toFixed(2);
				}
			)
		};

		$scope.chageBitSize = function() {
			srvInfo.changeBitSize($scope.bitSize.code);
		};

		$scope.changeCodingType = function(data) {
			$scope.isCoding = !$scope.isCoding;
			document.getElementById('incode').value = document.getElementById('outcode').value;
			document.getElementById('outcode').value = "";

			if ($scope.isCoding) {
				document.getElementById('incode').placeholder = "Text to code...";
				document.getElementById('outcode').placeholder = "Code...";
			}
			else {
				document.getElementById('incode').placeholder = "Code to decode...";
				document.getElementById('outcode').placeholder = "Original text...";
			}

		};
}]);

angular.module('myAppServices', [])
    .service('srvInfo',
             function($http) {
				 this.encode = function(callback) {
					return $http.get('/ajax/lzwpy/encode/?text='+document.getElementById('incode').value).then(callback);
				 };
				 this.decode = function(callback) {
					return $http.get('/ajax/lzwpy/decode/?text='+document.getElementById('incode').value).then(callback); 
				 };
				 this.changeBitSize = function(data) {
					 return $http.get('/ajax/lzwpy/changeBitSize/?bitSize='+data);
				 }
				 this.getCompressionRate = function(callback) {
					return $http.get('/ajax/lzwpy/getCompressionRate/').then(callback); 
				 }
             });


