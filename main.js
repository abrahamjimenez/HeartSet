import changeHue from "./changeHue.mjs"

function fetchCurrentValue() {
    fetch('/getCurrentValue')
        .then(response => response.json())
        .then(data => {
            document.getElementById('currentValue').innerText = data.heartRate;
        });
    changeColor(data.heartRate);
}

function changeColor(heartRate) {
    if (heartRate >= 130) {
        let darkValue = changeHue("#063509", 80)
        let midValue = changeHue("#677a6c", 80)
        let lightValue = changeHue("#dfebe2", 80)
        document.documentElement.style.setProperty("background-color", darkValue);
        // document.documentElement.style.setProperty("background-color", midValue);
        // document.documentElement.style.setProperty("color", lightValue);
    }
    else if (heartRate < 60) {
        let darkValue = changeHue("#063509", -120)
        let midValue = changeHue("#677a6c", -120)
        let lightValue = changeHue("#dfebe2", -120)
        document.documentElement.style.setProperty("background-color", darkValue);
        // document.documentElement.style.setProperty("background-color", midValue);
        // document.documentElement.style.setProperty("color", lightValue);
    }
}

setInterval(fetchCurrentValue, 5000);