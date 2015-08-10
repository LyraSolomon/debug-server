app.controller('GraphController', ['$scope', '$interval',
	function($scope, $interval)
{
	$scope.plots=[];
	$scope.refresh=function(){
		$scope.plots=[
		{
			title: 'qwe',
			y: 'distance',
			img: 'qwe.svg',
			val: 5
		},
		{
			title: 'hfsc',
			y: 'distance',
			img: 'hsfc.svg',
			val: 4
		}];
	};
	$scope.intervalPromise=$interval(function(){
		$scope.refresh();
	}, 3000);
	$scope.refresh();
}]);