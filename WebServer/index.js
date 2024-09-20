const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

// Để phục vụ file HTML từ vị trí chính xác
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html')); // Đường dẫn đến index.html
});

// API để điều khiển đèn LED
let ledState = 'off'; // Trạng thái đèn LED mặc định

app.get('/led', (req, res) => {
  res.send(ledState);
});

app.get('/led/:state', (req, res) => {
  const state = req.params.state;
  
  if (state === 'on' || state === 'off') {
    ledState = state;  // Cập nhật trạng thái đèn LED
    console.log(`Đèn LED đã được chuyển sang ${state}`);
    res.send(`Đèn LED đã được chuyển sang ${state}`);
  } else {
    res.status(400).send('Yêu cầu không hợp lệ');
  }
});

// Đảm bảo server đang lắng nghe trên cổng 3000
app.listen(port, () => {
  console.log(`Server đang chạy tại http://192.168.1.3:${port}`);
});
