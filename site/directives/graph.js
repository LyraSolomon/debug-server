app.directive('graph', function()
{
	return
	{
		restrict: 'E',
		scope:
		{
			graph: '='
		},
		templateUrl: 'directives/graph.html'
	};
});