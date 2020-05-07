angular.module('LZW', ['myAppControllers', 'myAppServices'] );

var myAppControllers = angular.module('myAppControllers', []);

myAppControllers.controller('codeController',
	['$scope', 'srvInfo',
		function ($scope, srvInfo) {

		$scope.isCoding = Boolean(true);

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

		};

		$scope.changeCodingType = function(data) {
			$scope.isCoding = !$scope.isCoding;
			document.getElementById('incode').value = "";
			document.getElementById('outcode').value = "";

			if ($scope.isCoding) {
				document.getElementById('incode').placeholder = "Tekst do zakodowania...";
				document.getElementById('outcode').placeholder = "Zakodowany tekst...";
			}
			else {
				document.getElementById('incode').placeholder = "Kod do odkodowania...";
				document.getElementById('outcode').placeholder = "Oryginalny tekst...";
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


