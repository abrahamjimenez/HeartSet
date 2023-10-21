const express = require('express');
const app = express();
const port = 6969

app.get('/', (req, res) =>{
	res.sendFile("C:/Users/sasal/Desktop/Projects/HeartSet/public/index.html")
})

app.listen(port, () => {
	console.log(`Server is running on port ${port}`);
});

// npm init -y > pnpm install > pnpm setup > pnpm install express > pnpm install sass > pnpm start