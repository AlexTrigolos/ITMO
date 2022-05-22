import { ApiProperty } from '@nestjs/swagger';
import { ValidateIf } from 'class-validator';

export class CreateUserDto {
  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  readonly email: string;

  @ApiProperty({ required: false })
  @ValidateIf((object, value) => value !== undefined)
  readonly name?: string;
}
