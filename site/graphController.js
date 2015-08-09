app.controller('GraphController', ['$scope', function($scope)
{
	$scope.plots=[
	{
		title: 'qwe',
		x: 'time',
		y: 'distance',
		data: [
		{
			color: 'green',
			data: [1, 2, 3, 2, 5]
		},
		{
			color: 'red',
			data: [5,2,3,4,5]
		}]
	},
	{
		title: 'hfsc',
		x: 'time',
		y: 'distance',
		data: [
		{
			color: 'green',
			data: '1, 2, 3, 2, 5'
		},
		{
			color: 'red',
			data: [5,2,3,4,5]
		}]
	}];
}]);