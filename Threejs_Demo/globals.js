var camera;
var scene;
var controls;
var time = Date.now();

var treeObj;
var mountainObj;

var treeModel;
var mountainModel;

var focusManager;
var levelManager;
var displayManager;

//temporary testing variables
var xmlDoc;
var mesh;
var box;
var directionalLight;
var mountains;



var utils={
  "jsonLoader" :new THREE.JSONLoader(),
  "xmlhttpreq": new XMLHttpRequest(),
  "domparser":new DOMParser()
};

displayManager = {

  "display":document.getElementById("display"),
  
  "renderer": new THREE.WebGLRenderer(),
  
  "init":function(){
    
    camera = new THREE.PerspectiveCamera(75, displayManager.renderer.domElement.width / displayManager.renderer.domElement.height, 0.1, 10000);
    
    
    
    scene = new THREE.Scene();
    
    window.onfocus = window.onblur = function(e) {
      focusManager.focused = (e || event).type === "focus";
    }

    window.onresize = displayManager.resize;

    levelManager.levels=[];
    levelManager.currentLevel=0;

    //remove loading message              
    displayManager.display.removeChild(display.children[0]);

    displayManager.renderer.setSize(1, 1);
    displayManager.display.appendChild(displayManager.renderer.domElement);

    camera.position.set(0,110,115);
    camera.lookAt(0,0,0);
    //camera.eulerOrder="YXZ";//precedence for changing axis, to  ensure proper rotation
    camera.up = new THREE.Vector3(0,0,1);
    camera.lookAt(0,0,0);
    camera.updateProjectionMatrix();
    scene.add(camera);

    controls = new THREE.OrbitControls( camera );              
  },
  
  "resize":function(){
  
    var displayWidth;
    var displayHeight;

    if(window.innerHeight / window.innerWidth < 1.61){
      displayWidth = window.innerWidth*0.7;
      displayHeight = displayWidth / 1.61;
    }else{
      displayHeight = window.innerHeight*0.7;
      displayWidth = displayHeight * 1.61;
    }

    displayManager.renderer.setSize(displayWidth, displayHeight);

    camera.aspect = displayWidth/displayHeight;
    camera.updateProjectionMatrix();

  },
  
  "render":function(){
    dt = Date.now() - time;
    //camera.position.set(110 * Math.cos(Math.PI*2 / 10000* dt), 110 * Math.sin(Math.PI*2 / 10000* dt),115);
    //camera.lookAt(0,0,0);
    mountains.rotation.y = -1.1*Math.sin(Math.PI*2 / 10000* dt) - 0.2;
    mesh.rotation.y = -1.1*Math.sin(Math.PI*2 / 10000* dt) - 0.2;
    //directionalLight.position.set( Math.cos(Math.PI*2 / 10000* dt), 1, Math.sin(Math.PI*2 / 10000* dt)).normalize();
    
    
    displayManager.renderer.render(scene, camera);
    window.requestAnimationFrame(displayManager.render);
    /*
    if(!focusManager.focused){

      if(focusManager.firstUnfocused){

        
        focusManager.firstUnfocused=false;
      }

    }else{

      if(!focusManager.firstUnfocused){

        focusManager.firstUnfocused=true;
      }



      displayManager.renderer.render(scene, camera);
      window.requestAnimationFrame(displayManager.render);
    }*/
  }
}

function Level(name, geography, scenery, render){
  this.name = name;
  this.geography = geography;
  this.scenery = scenery;
  this.render = render;
}

function Player(name, mesh, XYRotation, keycodes, init, dz, gravity){
  this.name = name;
  this.mesh = mesh;
  this.XYRotation = XYRotation;
  this.keycodes = keycodes;
  this.key_flag = {"u":0,"d":0,"l":0,"r":0, "z":0};
  this.init = init;
  this.dz = dz;
  this.gravity = gravity;
}

focusManager = {
  "focused" : true,
  "firstUnfocused" : true
}

levelManager = {
  "loadLevel":function(){
    
    function onlevelload(){  
      
      treeModel = utils.jsonLoader.parse(treeObj);
      mesh = new THREE.Mesh(treeModel.geometry, new THREE.MeshLambertMaterial({"color":0x00ff00}));
      mesh.position.x = 0;
      mesh.position.y = 0;
      mesh.position.z = 22;
      mesh.scale.x = 2;
      mesh.scale.z = 2;
      mesh.scale.y = 2.5;
      mesh.rotation.x = Math.PI/2;
      mesh.castShadow = true;
      mesh.receiveShadow = false;
      
      scene.add(mesh);
      
      mountainModel = utils.jsonLoader.parse(mountainObj);
      mountains = new THREE.Mesh(mountainModel.geometry, new THREE.MeshPhongMaterial({"color":0xa55814}));
      mountains.scale.x = 100;
      mountains.scale.y = 100;
      mountains.scale.z = 100;
      mountains.position.x = 0;
      mountains.position.y = 0;
      mountains.position.z = 0;
      mountains.rotation.x = Math.PI/2;
      mountains.castShadow = false;
      mountains.receiveShadow = true;
      scene.add(mountains);
        
        
    }
      
    
    
    /*utils.xmlhttpreq.addEventListener("load", onlevelload);
    
    utils.xmlhttpreq.open("GET","./src/level_layouts/level_1.xml", false);
    
    utils.xmlhttpreq.send();*/
    
    onlevelload();
    
    


    directionalLight = new THREE.DirectionalLight( 0xffffff);
    directionalLight.position.set( 1, 1, 0.5).normalize();
    directionalLight.castShadow = true;
    
    

    scene.add( directionalLight );
    
  },
  "currentLevel":0,
  "levels":[]
}
