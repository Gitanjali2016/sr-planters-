import com.temboo.core.*;
import com.temboo.Library.Twitter.Search.*;

// Create a session using your Temboo account application details
TembooSession session = new TembooSession("drones-lab", "myFirstApp", "g77WXvgnW7fP1nSfdeJCJuC5a2ZGQ760");

// The name of your Temboo Twitter Profile 
String twitterProfile = "yourTwitterProfile";

// Set up text strings
String searchText, tweetText;

// Create a JSON object to store the search results
JSONObject searchResults;

void setup() {
  // Set a search term and instructions
  searchText = "sandwich";

  // Display initial tweet
  runTweetsChoreo(); // Run the Tweets Choreo function
  getTweetFromJSON(); // Parse the JSON response
  displayText(); // Display the response
}

void runTweetsChoreo() {
  // Create the Choreo object using your Temboo session
  Tweets tweetsChoreo = new Tweets(session);

  // Set Profile
  tweetsChoreo.setCredential(twitterProfile);

  // Set inputs
  tweetsChoreo.setQuery(searchText);

  // Run the Choreo and store the results
  TweetsResultSet tweetsResults = tweetsChoreo.run();
  
  // Store results in a JSON object
  searchResults = parseJSONObject(tweetsResults.getResponse());
}

void getTweetFromJSON() {
  JSONArray statuses = searchResults.getJSONArray("statuses"); // Create a JSON array of the Twitter statuses in the object
  JSONObject tweet = statuses.getJSONObject(0); // Grab the first tweet and put it in a JSON object
  tweetText = tweet.getString("text"); // Pull the tweet text from tweet JSON object
}

void displayText() {
  println(tweetText); // Print tweet to console
}