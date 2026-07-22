<img width="600" alt="DebConf 26 - Edge Machine Learning" src="https://github.com/user-attachments/assets/ae98648c-7ee5-4576-8d71-6635610d857d" />

# 🤖 Edge Machine Learning on Debian
### DebConf 26 Demo Project

This repository contains the code and setup instructions for the live demo presented at **DebConf 26**.

The project demonstrates how to deploy an **Edge Impulse** Machine Learning model on Arduino UNO Q running Debian Trixie, using a USB webcam and Python, performing inference locally without relying on cloud services.

---

## 📖 Presentation

**Track:** Artificial Intelligence & Debian  
**Type:** Long Talk (45 min)

---

# 🛠 Requirements

| Component | Version |
|-----------|---------|
| Debian | 12+ |
| Node.js | 20 |
| Python | 3.x |
| USB Webcam | UVC Compatible |
| Edge Impulse Linux SDK | Latest |

---

# 📦 Installing Edge Impulse

Update the system:

```bash
sudo apt update
```

Install Node.js 20:

```bash
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo bash -
```

Install dependencies:

```bash
sudo apt install -y \
    gcc \
    g++ \
    make \
    build-essential \
    nodejs \
    sox \
    gstreamer1.0-tools \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-base-apps
```

Install the Edge Impulse Linux CLI:

```bash
sudo npm install -g edge-impulse-linux --unsafe-perm
```

---

# 🚀 Setup

Launch the Edge Impulse runner:

```bash
edge-impulse-linux-runner
```

Then:

1. 🔐 Log into your Edge Impulse account
2. 📁 Select the project
3. 📷 Choose the USB webcam
4. ⚙️ Select the quantized model
5. ▶️ Start inference

---

# 🐍 Arduino MCU Integration (optional)

Upload and execute the Arduino bridge:

```bash
$ nohup python3 bridge.py > bridge.log 2>&1 & 
```

This script allows Python to communicate with the Arduino during inference. Also upload the Arduino Sketch with AppLab.

---

# 🧠 Machine Learning Model

The model used during the presentation is available on Edge Impulse Studio:

🔗 https://studio.edgeimpulse.com/studio/1062918

---

# 📂 Repository Structure

```
.
├── arduino.py          # Arduino communication
├── bridge.py
└── ...
```

---

# 📚 References

- 🔗 Edge Impulse
  https://edgeimpulse.com

- 📖 Edge Impulse Linux SDK
  https://docs.edgeimpulse.com/docs/run-inference/linux

- 🐧 Debian
  https://www.debian.org

---

# 👤 Author

**Roni Bandini**

🔗 LinkedIn  
https://www.linkedin.com/in/ronibandini/

📝 AI & Machine Learning Articles  
https://bandini.medium.com/list/inteligencia-artificial-y-machine-learning-28ba49fa1e96

🌐 Website  
https://bandini.medium.com

---

# 📜 License

MIT
