import tweepy
import time
import array
import serial

ser = serial.Serial('/dev/ttyUSB0')

#Twitter info
consumer_key = '5evr04VvMIbVnPPcYH9Acavbz'
consumer_secret = 'Szu0gUJhG8vuvD3lY4YGu37JPgd1XkZ4waEXCsniUU147f6g9S'
access_token = '1027798144589881344-84yC8343RgvE6q7IiBmMkN0VItw01h'
access_token_secret = 'Ou67UFrWBgq7N7WuqrH5quK9D5wyxANvAZ6S7ZzZSCdX4'

#Manage Twitter data
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)
api = tweepy.API(auth,wait_on_rate_limit=True)

#Search Parameters
hashTag = "#donate"
searchTerm = "refugees"

#Pull from Twitter 
prevTweets = []
tweetStart = api.search(q=hashTag)

while True :
    for tweet in api.search(q = hashTag, since_id = tweetStart.since_id):
    #change tweet to tweet id to save memory?
        if ((not prevTweets.__contains__(tweet)) and tweet.text.__contains__(searchTerm)):
            #do things
            ser.write(tweet.text)
            #print("new tweet -" +  "CONTENTS: " + tweet.text)
            prevTweets.append(tweet)

    time.sleep(5)
