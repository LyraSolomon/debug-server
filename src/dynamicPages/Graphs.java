package dynamicPages;

import java.util.*;

public class Graphs extends DynamicPage {
	private ArrayList<Graph> contents;
	public Graphs(){
		contents=new ArrayList<Graph>();
		contents.add(new Graph());//for testing
		contents.get(0).title="graph1";
		contents.get(0).y="distance";
		contents.get(0).data=new ArrayList<Float>();
	}
	@Override
	public String getContent(String URL, Map<String, String> moreData) {
		if(URL.equals("add_graph_data.html"))
		{
			if(moreData.containsKey("data"))
			{
				Float f=Float.parseFloat(moreData.get("data"));
				contents.get(0).data.add(f);
				if(contents.get(0).data.size()==1)
				{
					contents.get(0).min=f;
					contents.get(0).max=f;
				}
				else
				{
					contents.get(0).min=Math.min(contents.get(0).min, f);
					contents.get(0).max=Math.max(contents.get(0).max, f);
				}
			}
			return "<html><body><form><input type=\"text\" name=\"data\" />"
					+ "<input type=\"submit\" /></form></html>";
		}
		if(URL.equals("dynamic_graphs.html"))
		{
			String retval="";
			for(int i=0; i<contents.size(); i++)
			{
				retval+="<h2>"+contents.get(i).title+"</h2>";
				retval+="<p>"+contents.get(i).y+"</p>";
				retval+="<svg width=\"150\" height=\"110\">";
				retval+="<polygon points=\"0,5 100,5 100,105, 0,105\" style="
						+ "\"fill:none;stroke:black;stroke-width:1;\" />";
				if(contents.get(i).max>contents.get(i).min)
				{
					retval+="<polyline points=\"";
					for(int j=0; j<contents.get(i).data.size(); j++)
					{
						retval+=j*100/(contents.get(i).data.size()-1);
						retval+=",";
						retval+=(-(contents.get(i).data.get(j)-contents.get(i).min)/
								(contents.get(i).max-contents.get(i).min)+1)*100+5;
						retval+=" ";
					}
					retval+="\" style=\"fill:none;stroke:blue;stroke-width:2;\" />";
					retval+="<text x=\"100\" y=\"10\" fill=\"black\">"+
							contents.get(i).max+"</text>";
					retval+="<text x=\"100\" y=\"110\" fill=\"black\">"+
							contents.get(i).min+"</text>";
				}
			}
			return retval;
		}
		else return null;
	}

}
class Graph {
	String title;
	String y;
	Float min=0f, max=0f;
	ArrayList<Float> data;
}