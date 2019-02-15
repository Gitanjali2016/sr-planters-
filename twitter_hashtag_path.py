import tweepy
import time

#Twitter info
consumer_key = '5evr04VvMIbVnPPcYH9Acavbz'
consumer_secret = 'Szu0gUJhG8vuvD3lY4YGu37JPgd1XkZ4waEXCsniUU147f6g9S'
access_token = '1027798144589881344-84yC8343RgvE6q7IiBmMkN0VItw01h'
access_token_secret = 'Ou67UFrWBgq7N7WuqrH5quK9D5wyxANvAZ6S7ZzZSCdX4'

#Manage Twitter data
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)
api = tweepy.API(auth,wait_on_rate_limit=True)

#Pull from Twitter 
prevTweet = ""
search = "Yeah no if you need anything you need me a little while to do something else I think it would probably work better if I had to do it I just got a new phone call me "
while True :
    for tweet in tweepy.Cursor(api.search,q=search).items():
    
        if (tweet.text != prevTweet):
            #do things
            print("*************************************")
            print("new tweet -" +  "CONTENTS: " + tweet.text)
        prevTweet = tweet.text
        print("old tweet -" +  "CONTENTS: " + tweet.text)
        time.sleep(1)
    #print(tweet.created_at, tweet.text)
    #csvWriter.writerow([tweet.created_at, tweet.text.encode('utf-8')])

