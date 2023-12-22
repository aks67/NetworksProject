
fetch('out.bin')
.then(response => response.arrayBuffer())
.then(buffer => {

    console.log(buffer);
})
.catch(error=>console.error('Error fetching data: ', error));