require 'rubygems' if RUBY_VERSION < "1.9"
require 'sinatra/base'
require "rdiscount"
require "haml"
require "sass"

class MyApp < Sinatra::Base
	get '/' do
	  haml :index
	end
	
	get '/heartbeat' do
	  "heartbeat response from webapp"
	end

	get '/style.css' do
	  header 'Content-Type' => 'text/css; charset=utf-8'
	  sass :stylesheet
	end
end

MyApp.run!