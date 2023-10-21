const express = require('express');
const app = express();
const port = 6969


app.get('/', (req, res) => {
	res.send('Hello, Express.js!');
});

app.listen(port, () => {
	console.log(`Server is running on port ${port}`);
});

// npm init -y > pnpm install > pnpm setup > pnpm install express > pnpm install sass > pnpm start