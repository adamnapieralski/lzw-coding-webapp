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

		$scope.encode = function(data) {
			if ($scope.isCoding) {
				console.log("encode");
				srvInfo.encode(
					function(data) {
						$scope.out = data.data;
						console.log(data);
					});
			}
			else {
				console.log("decode");
				srvInfo.decode(
					function(data) {
						$scope.out = data.data;
						console.log(data);
					});
			}
			srvInfo.getCompressionRate(
				function(data) {
					$scope.compressionRate = data.data.CR.toFixed(2);
					console.log($scope.compressionRate);
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
	

// communication with the server
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
                //  this.findTile = function(callback) {
				// 	 // wywoluje findTile z checkerspy/views.py
                //      return $http.get('/ajax/checkerspy/findTile/?pawn_id='+document.getElementById('pawn_id').value).then(callback);
				//  };
				//  this.initializeGame = function(callback) {
				// 	var colors = document.getElementsByName('userColors'); 
				// 	var user_color = "";
				// 	for(i = 0; i < colors.length; i++) { 
				// 		if(colors[i].checked) 
				// 			user_color = colors[i].value;
				// 	} 
				// 	return $http.get('/ajax/checkerspy/initialize/?user_name='
				// 	+ document.getElementById('userNameText').value + '&user_color='
				// 	+ user_color).then(callback); 
				//  };
				//  this.getUserName = function(callback) {
				// 	return $http.get('/ajax/checkerspy/get_user_data/').then(callback); 
				//  };

             });


