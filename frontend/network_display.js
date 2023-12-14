// script.js

document.getElementById('fileInput').addEventListener('change', handleFileSelect);

function handleFileSelect(event) {
    const fileInput = event.target;
    const file = fileInput.files[0];

    if (file) {
        const reader = new FileReader();

        reader.onload = function (e) {
            const content = e.target.result;
            displayFileContent(content);
        };

        reader.readAsText(file);
    }
}

function displayFileContent(content) {
    const outputElement = document.getElementById('output');
    outputElement.textContent = content;
}
