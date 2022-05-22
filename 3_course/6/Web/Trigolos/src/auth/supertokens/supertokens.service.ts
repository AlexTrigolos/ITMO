import { Inject, Injectable } from '@nestjs/common';
import { ConfigInjectionToken, AuthModuleConfig } from '../config.interface';
import supertokens from 'supertokens-node';
import Session from 'supertokens-node/recipe/session';
import ThirdPartyEmailPassword from 'supertokens-node/recipe/thirdpartyemailpassword';
import EmailPassword from 'supertokens-node/recipe/emailpassword';
const { Google, Github, Apple } = ThirdPartyEmailPassword;

@Injectable()
export class SupertokensService {
  constructor(@Inject(ConfigInjectionToken) private config: AuthModuleConfig) {
    supertokens.init({
      framework: 'express',
      supertokens: {
        // These are the connection details of the app you created on supertokens.com
        connectionURI:
          'https://9baf5c31c54c11eca199e7bd956c96c9-us-east-1.aws.supertokens.io:3568',
        apiKey: 'YqBHwryoT=rYJOoOlpFmrFIE7pyoY0',
      },
      appInfo: {
        // learn more about this on https://supertokens.com/docs/session/appinfo
        appName: 'trigolos-web-app',
        apiDomain: 'http://localhost:12345',
        websiteDomain: 'http://localhost:3000',
        apiBasePath: '/auth',
        websiteBasePath: '/auth',
      },
      recipeList: [
        EmailPassword.init(), // initializes signin / sign up features
        Session.init(), // initializes session features
      ],
    });
  }
}
