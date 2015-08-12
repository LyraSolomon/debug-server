package dynamicPages;

import java.util.*;

public class Graphs extends DynamicPage {
	private ArrayList<Graph> contents;
	private Integer historySize=100;
	public Graphs(){
		contents=new ArrayList<Graph>();
		contents.add(new Graph());//for testing
		contents.get(0).title="graph1";
		contents.get(0).data=new ArrayList<Float>();
	}
	@Override
	public String getContent(String URL, Map<String, String> moreData) {
		if(URL.equals("add_graph_data.html"))
		{
			if(moreData.containsKey("title")&&moreData.containsKey("data"))
			{
				int index=-1;
				for(int i=0; i<contents.size(); i++)
				{
					if(contents.get(i).title.equals(moreData.get("title")))
					{
						index=i;
						break;
					}
				}
				if(index==-1)
				{
					contents.add(new Graph());
					index=contents.size()-1;
					contents.get(index).title=moreData.get("title");
					contents.get(index).data=new ArrayList<Float>();
				}
				Float f=Float.parseFloat(moreData.get("data"));
				contents.get(index).data.add(f);
				if(contents.get(index).data.size()==1)
				{
					contents.get(index).min=f;
					contents.get(index).max=f;
				}
				else
				{
					contents.get(index).min=Math.min(contents.get(index).min, f);
					contents.get(index).max=Math.max(contents.get(index).max, f);
				}
			}
			return "<html><body><form>value:<input type=\"text\" name=\"data\" /><br />"
					+ "title:<input type=\"text\" name=\"title\" value=\""
					+ moreData.get("title")+"\"/><br /><input type=\"submit\" /></form></html>";
		}
		if(URL.equals("graphs.html"))
		{
			if(moreData.containsKey("size")) historySize=Integer.parseInt(moreData.get("size"));
			return "<!doctype html><html><head><script src=\"jquery-2.1.4.min.js\"></script>"
				+ "<script>$(function(){setInterval(function(){"
				+ "$('#include').load('dynamic_graphs.html');}, 300);});"
				+ "</script></head><body><div id=\"foo\"></div><form id=\"history\">"
				+ "history size:<input type=\"text\" name=\"size\">"
				+ "<input type=\"submit\"></input></form>"
				+ "<div id=\"include\"></div></body></html>";
		}
		if(URL.equals("dynamic_graphs.html"))
		{
			String retval="";
			for(int i=0; i<contents.size(); i++)
			{
				retval+="<h2>"+contents.get(i).title+"</h2>";
				retval+="<svg width=\"200\" height=\"110\">";
				retval+="<polygon points=\"0,5 100,5 100,105, 0,105\" style="
						+ "\"fill:none;stroke:black;stroke-width:1;\" />";
				if(contents.get(i).max>contents.get(i).min&&historySize>1)
				{
					retval+="<polyline points=\"";
					int start=Math.max(0, contents.get(i).data.size()-historySize);
					for(int j=start; j<contents.get(i).data.size(); j++)
					{
						retval+=(j-start)*100/(contents.get(i).data.size()-start-1);
						retval+=",";
						retval+=(-(contents.get(i).data.get(j)-contents.get(i).min)/
								(contents.get(i).max-contents.get(i).min)+1)*100+5;
						retval+=" ";
					}
					retval+="\" style=\"fill:none;stroke:blue;stroke-width:2;\" />";
					retval+="<text x=\"100\" y=\"10\" fill=\"black\">"+
							contents.get(i).max+"</text>";
					retval+="<text x=\"100\" y=\"110\" fill=\"black\">"+
							contents.get(i).min+"</text></svg>";
				}
				if(contents.get(i).data.size()>0) 
					retval+="<p>currently: "+
						contents.get(i).data.get(contents.get(i).data.size()-1)+"</p>";
			}
			return retval;
		}
		else return null;
	}

}
class Graph {
	String title;
	Float min=0f, max=0f;
	ArrayList<Float> data;
}