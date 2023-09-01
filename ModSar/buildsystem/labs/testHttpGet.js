const http = require("http") 
const option = {
	//host: '127.0.0.1',
//	port: 3128,
	path: "https://www.baidu.com" ,
};
http.get("http://www.baidu.com",(res)=>{
    var html = ""
    res.on("data",(data)=>{
        html+=data
    })

    res.on("end",()=>{
        console.log(html)
    })
}).on("error",(e)=>{
	var xx = 2;
    console.log(`error: ${e.message}= ${xx}`)
});