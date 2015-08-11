package dynamicPages;

import java.util.Map;

public abstract class DynamicPage {
	/** gets contents of a dynamic page
	 * 
	 * @param URL the URL of the page
	 * @param moreData GET or POST data
	 * @return the contents if it exists, otherwise null
	 */
	public abstract String getContent(String URL, Map<String, String> moreData);
}
