# Use the custom made systemC container I've made. This is from: the VSCode python container.
ARG VARIANT="python3-bullseye"
FROM smattacus/systemc:$VARIANT

RUN pip install pip --upgrade

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-packages>

# [Optional] Uncomment this line to install global node packages.
# RUN su vscode -c "source /usr/local/share/nvm/nvm.sh && npm install -g <your-package-here>" 2>&1