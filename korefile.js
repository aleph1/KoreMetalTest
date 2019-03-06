let project = new Project('KoreMetalTest');

project.addFile('Sources/**');
project.setDebugDir('Deployment');

resolve(project);
